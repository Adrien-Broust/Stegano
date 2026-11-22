#include "Message.h"
#include "Bits.h"
#include <stdexcept>

void Message::ApplyXor(std::vector<std::uint8_t>& data, const std::string& key)
{
    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] ^= static_cast<std::uint8_t>(key[i % key.size()]);
}

// Écrit chaque bit de 'bytes' dans le bit de poids faible d'un octet du support
void Message::WriteBytes(std::vector<std::uint8_t>& carrier, std::size_t start,
    const std::vector<std::uint8_t>& bytes)
{
    for (std::size_t i = 0; i < bytes.size(); ++i)
    {
        for (unsigned int b = 0; b < 8; ++b)
        {
            bool bit = Bits::GetBit(bytes[i], 7 - b);
            std::size_t pos = start + i * 8 + b;

            carrier[pos] = bit ? Bits::SetBit(carrier[pos], 0)
                : Bits::ClearBit(carrier[pos], 0);
        }
    }
}

// Relit exactement 'count' octets depuis les bits de poids faible
std::vector<std::uint8_t> Message::ReadBytes(const std::vector<std::uint8_t>& carrier,
    std::size_t start, std::size_t count)
{
    std::vector<std::uint8_t> result(count, 0);

    for (std::size_t i = 0; i < count; ++i)
    {
        for (unsigned int b = 0; b < 8; ++b)
        {
            if (Bits::GetBit(carrier[start + i * 8 + b], 0))
                result[i] = Bits::SetBit(result[i], 7 - b);
        }
    }
    return result;
}

void Message::Embed(std::vector<std::uint8_t>& carrier, std::size_t start,
    const std::string& text, const std::string& key)
{
    std::vector<std::uint8_t> payload(text.begin(), text.end());
    std::uint8_t flags = 0;

    if (!key.empty())
    {
        ApplyXor(payload, key);
        flags = Bits::SetBit(flags, FlagXor);
    }

    std::vector<std::uint8_t> msg = { 'S', 'T', 'E', 'G', flags };
    std::uint32_t len = static_cast<std::uint32_t>(payload.size());
    msg.push_back((len >> 24) & 0xFF);
    msg.push_back((len >> 16) & 0xFF);
    msg.push_back((len >> 8) & 0xFF);
    msg.push_back(len & 0xFF);
    msg.insert(msg.end(), payload.begin(), payload.end());

    if (start + msg.size() * 8 > carrier.size())
        throw std::runtime_error("Image trop petite pour ce message");

    WriteBytes(carrier, start, msg);
}

std::string Message::Extract(const std::vector<std::uint8_t>& carrier,
    std::size_t start, const std::string& key)
{
    if (start + HeaderSize * 8 > carrier.size())
        throw std::runtime_error("Image trop petite");

    auto header = ReadBytes(carrier, start, HeaderSize);

    if (header[0] != 'S' || header[1] != 'T' || header[2] != 'E' || header[3] != 'G')
        throw std::runtime_error("Aucun message trouve");

    std::uint8_t flags = header[4];
    std::uint32_t len = (std::uint32_t(header[5]) << 24)
        | (std::uint32_t(header[6]) << 16)
        | (std::uint32_t(header[7]) << 8)
        | std::uint32_t(header[8]);

    if (start + (HeaderSize + len) * 8 > carrier.size())
        throw std::runtime_error("Longueur invalide");

    auto payload = ReadBytes(carrier, start + HeaderSize * 8, len);

    if (Bits::GetBit(flags, FlagXor))
    {
        if (key.empty())
            throw std::runtime_error("Message chiffre : cle requise");
        ApplyXor(payload, key);
    }

    return std::string(payload.begin(), payload.end());
}