FROM gcc:latest
RUN apt-get update && \
    apt-get install -y cmake git && \
    rm -rf /var/lib/apt/lists/*
COPY . /usr/src/mytest
WORKDIR /usr/src/mytest
RUN rm -rf build
RUN mkdir -p build
WORKDIR /usr/src/mytest/build
RUN cmake .. && make
WORKDIR /usr/src/mytest/build
CMD ["./tests"]
