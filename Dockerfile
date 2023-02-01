FROM alpine:3.17

RUN apk update && apk add --no-cache libstdc++

ADD bin/model_app /usr/local/bin
# ADD certs /opt/um/certs

WORKDIR /opt/um

ENTRYPOINT ["model_app"]
# CMD ["dist", "certs", "-a", "0.0.0.0", "-p", "8443", "-n", "4"]
