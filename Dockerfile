FROM debian:jessie

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends curl ca-certificates build-essential && \
    rm -rf /var/lib/apt/lists
RUN curl -sL https://deb.nodesource.com/setup_9.x | bash - && \
    apt-get install -y --no-install-recommends nodejs && \
    rm -rf /var/lib/apt/lists

WORKDIR /build
ENTRYPOINT [ "/build/node_modules/.bin/node-pre-gyp" ]
