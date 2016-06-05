Hello: Hello.c HelloFunc.c
	gcc -o hello Hello.c HelloFunc.c -I.

JogoTiro: Player.c CollisionManager.c MonoBehaviour.c Enemy.c Window.c JogoTiro.c
	cc -o JogoTiro Player.c CollisionManager.c MonoBehaviour.c Enemy.c Window.c JogoTiro.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm -I.
