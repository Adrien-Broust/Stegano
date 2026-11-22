Adrien Broust
Cyril Rada

Le code utilise 2 classes: 

Message qui gère l'encodage et le décodage du message 

Files qui lui gère le fichier BMP

pour utiliser le code il faut choisir l'image que vous voulez utiliser et l'ouvrir avec la fonction openFilebmp dans le main (il n'y a pas d'implémentation de CLI)

ensuite choisir le mot que vous voulez cacher dans l'image avec Embed vous pouvez choisir dans quelle colonne et ligne vous voulez cachez le message

puis le décoder avec Extract avec la position et la clé

Exemple:




Files imageApple;

imageApple.openFileBmp("Apple.bmp");

Message message;

message.Embed(imageApple, 0, 0, 0, "Bonjour", "Poire");

std::string result = message.Extract(imageApple, 0, 0, 0, "Poire");

std::cout << result << std::endl;
