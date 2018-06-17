function tlpi {
	docker run --security-opt seccomp:unconfined --rm -ti \
	  -v $PWD/src:/src \
	  yago/tlpi
}
