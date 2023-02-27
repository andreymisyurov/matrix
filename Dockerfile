FROM alpine:3.14
WORKDIR /Matrix
COPY ./my_matrix.h /Matrix
COPY ./Makefile /Matrix
COPY ./test.cc /Matrix
COPY ./linters /Matrix/linters
RUN apk update && \
    apk add --no-cache build-base gtest-dev cmake valgrind python3 cppcheck && \
    rm -rf /var/cache/apk/*
CMD ["make", "all"]
