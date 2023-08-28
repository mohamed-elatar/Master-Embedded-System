@@mohamed elatar (learn-in-depth)
.global reset
reset:
		ldr sp, = stack_top
		bl main
stop: b stop