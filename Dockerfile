FROM gcc:latest
RUN apt-get update && \
    apt-get install -y cmake git && \
    rm -rf /var/lib/apt/lists/*
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN rm -rf build && mkdir -p build
WORKDIR /usr/src/myapp/build
RUN cmake .. && make
RUN mkdir -p /usr/src/myapp/data && chmod 777 /usr/src/myapp/data
#deciding what to run, default run the code, test to run the tests
RUN echo '#!/bin/bash' > /entrypoint.sh && \
    echo 'mkdir -p /usr/src/myapp/data' >> /entrypoint.sh && \
    echo 'cd /usr/src/myapp/build' >> /entrypoint.sh && \
    echo 'if [ "$1" = "test" ]; then' >> /entrypoint.sh && \
    echo '  ./tests' >> /entrypoint.sh && \
    echo 'else' >> /entrypoint.sh && \
    echo '  ./gomail' >> /entrypoint.sh && \
    echo 'fi' >> /entrypoint.sh && \
    chmod +x /entrypoint.sh
WORKDIR /usr/src/myapp/build
ENTRYPOINT ["/entrypoint.sh"]
#default run main
CMD []