FROM debian:9.4

RUN apt-get update && apt-get -y install \
    make \
    gcc \
    libcap-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /tlpi
ADD docker/ .

RUN cd tlpi-dist \
 && make \
 && cp libtlpi.a ../ \
 && cp -r lib ../ \
 && cd -

ENTRYPOINT ./entrypoint.sh
