à faire : 
- le temps sécoule trop rapidement dans les graphiques
- find_material doit retourner un objet si non trouvé ?
- keff calculation : disable neutron creation already pushed.
- problem fission bank when neutron creation enabled
- decentering a t'il besoin d'un vecteur SFML ? Peut-être ce serait mieux que je créée ma propre classe de vecteur pour éviter la dépendance des classes de bas niveau.
- éviter la dépendance de Particle avec SFML clock
- problème dépendances : SFML est donné par librairie .so (binaire). TGUI a été recompilé. Il faudrait qu'il n'y ait que les sources et qu'on les recompile automatiquement.
- pb de scène dont la largeur ne va pas jusqu'au menu.

04/02/24 : 
- added a script to compile and launch the project in release and debug mode
- added a launch.json configuration for vscode
- added the ability to automatically unzip the SFML and TGUI dependencies before compilation.

01/02/24 
- keff computation corrected
- keff_estimator_coll_tot added
- improved keff sigma calculation
- automatic_computed_keff can now be set in the input file
