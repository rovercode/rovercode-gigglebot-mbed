FROM ubuntu:20.04

RUN mkdir /app
WORKDIR /app

RUN apt update && apt install -y \
    clang-format

ENTRYPOINT ["clang-format"]
CMD [""]
