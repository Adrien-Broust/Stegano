#include "Message.h"
#include "Bits.h"
#include <stdexcept>

void Message::ApplyXor(std::vector<std::uint8_t>& data, const std::string& key)
{
    if (key.empty())
		throw std::invalid_argument("La cle ne peut pas etre vide");
    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] ^= static_cast<std::uint8_t>(key[i % key.size()]);
}

void Message::Embed(Files& image, uint32_t row, uint32_t column,
    uint32_t channel, const std::string& text, const std::string& key)
{
    std::vector<uint8_t> payload(text.begin(), text.end());

    uint8_t flags = 0;

    if (!key.empty())
    {
        ApplyXor(payload, key);
        flags = Bits::SetBit(flags, FlagXor);
    }

    std::vector<uint8_t> msg = { 'S', 'T', 'E', 'G', flags };

    uint32_t len = static_cast<uint32_t>(payload.size());

    msg.push_back((len >> 24) & 0xFF);
    msg.push_back((len >> 16) & 0xFF);
    msg.push_back((len >> 8) & 0xFF);
    msg.push_back(len & 0xFF);

    msg.insert(msg.end(), payload.begin(), payload.end());

    image.WriteBytes(row, column, channel, msg);
}

std::string Message::Extract(Files& image, uint32_t row,
    uint32_t column, uint32_t channel,
    const std::string& key)
{
    std::vector<uint8_t> header = image.ReadBytes(row, column, channel, 9);

    if (header[0] != 'S' || header[1] != 'T' ||
        header[2] != 'E' || header[3] != 'G')
    {
        throw std::runtime_error("Aucun message trouve");
    }

    uint8_t flags = header[4];

    uint32_t len =
        (uint32_t(header[5]) << 24) |
        (uint32_t(header[6]) << 16) |
        (uint32_t(header[7]) << 8) |
        uint32_t(header[8]);
    std::vector<uint8_t> payload =
        image.ReadBytes(row, column + 9 * 8, channel, len);
    if (Bits::GetBit(flags, FlagXor))
    {
        if (key.empty())
            throw std::runtime_error("Cle requise");

        ApplyXor(payload, key);
    }

    return std::string(payload.begin(), payload.end());
}