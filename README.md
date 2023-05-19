# APP2_S6

## Une station météo branchée

Dans le contexte global d’une prise de conscience de l’état de la planète et plus spécifiquement des
impacts de l’évolution du climat, vous décidez de créer votre propre entreprise axée sur le développement
de produits contribuant au suivi collectif des données climatiques. Le premier produit que vous visez est
une station météo connectée de milieu de gamme permettant de partager via un site WEB les principales
mesures météorologiques.
Ces mesures seront la température, l’humidité relative, la pression barométrique, l’ensoleillement, la
quantité de précipitation et la direction et la vitesse du vent. Elles seront collectées via a un ensemble de
capteurs par une ou plusieurs stations alimentées par énergie solaire. Un microcontrôleur sur la station
fera la lecture de ces capteurs en continu via différentes interfaces d’entrées/sorties et les données seront
ensuite transmises à une station de base branchée sur le secteur puis retransmise vers un serveur. Ces
données pourront ensuite être visualisées en temps réel sur une page WEB hébergée par le même serveur.
À des fins de démonstration pour obtenir du financement pour votre entreprise vous décidez de réaliser
un prototype fonctionnel de la station météorologique. Un kit de développement vous a été fourni. Même
si le prototype fonctionnel développé sera construit en utilisant des microcontrôleurs et des capteurs du
commerce actuellement disponibles, vous réalisez que pour diminuer les coûts de la plateforme ainsi que
sa consommation électrique, il sera nécessaire de modifier certains choix technologiques pour la version
commerciale. 

## MANDAT

La conception d’un prototype complet prend normalement plus de temps qu’une seule semaine. Ainsi,
les choix des pièces sont déjà faits pour vous. Voici la liste des fonctionnalités demandées.
  - Lecture des différents capteurs (température, l’humidité relative, pression barométrique, ensoleillement,
la quantité de précipitation, direction et la vitesse du vent ) et transformation des mesures en unités
standardisées.
  - Programmation d’un lien UART entre deux Argons, l’un servant de station de base, l’autre de station de
capteurs. Lors de la réception d’une commande provenant de la station de base, les données des capteurs
sont transmises par la station de capteurs vers la station de base.
  - Remplacer ce lien UART par un service BLE notifiant automatiquement la station de base lors des
modifications des valeurs des différents capteurs.

Il faut aussi évaluer les modifications à apporter pour la version commerciale du prototype, notamment
vous devez aborder :
  - Choix des technologies de communication sans fil
  - Choix des capteurs, tout particulièrement le capteur d’intensité lumineuse pour mesurer la durée
d’ensoleillement et l’anémomètre utilisé pour mesurer la direction et la vitesse du vent. Vous devez
effectuer une étude sommaire pour identifier les technologies alternatives qui pourraient être utilisées pour
ces capteurs, leurs avantages et leurs inconvénients. Identifier clairement la solution que vous utiliseriez
dans un produit commercial.
  - Choix du microcontrôleur et des interfaces d’entrées/sorties

Vous devez analyser ces aspects en fonction des fonctionnalités requises sur votre station, de la
consommation électrique, de la robustesse et de la mise à l’échelle (plusieurs stations de capteurs
connectées sur une seule station de base). Si vous jugez que la solution prototype est adéquate pour la
version commerciale, vous devez quand même justifier ce choix en le comparant à des alternatives.
