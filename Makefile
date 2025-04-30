all:
	gbacc main.c pong.c gba.c layout.c ball_logic.c ball_state.c collision.c score.c cpu.c render.c -o pong.gba
