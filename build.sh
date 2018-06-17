function tlpi {
	docker run --rm -ti \
	  -v $PWD/src:/src \
	  yago/tlpi
}
