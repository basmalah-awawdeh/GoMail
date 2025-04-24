FROM gcc:latest
RUN apt-get update && \
    apt-get install -y cmake git && \
    rm -rf /var/lib/apt/lists/*
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN rm -rf build
RUN mkdir -p build
WORKDIR /usr/src/myapp/build
RUN cmake .. && make
RUN mkdir -p data
#deciding what to run, default run the code, test to run the tests
RUN echo '#!/bin/bash' > /usr/src/myapp/run.sh && \
    echo 'if [ "$1" = "test" ]; then' >> /usr/src/myapp/run.sh && \
    echo '  cd /usr/src/myapp/build && ./tests' >> /usr/src/myapp/run.sh && \
    echo 'else' >> /usr/src/myapp/run.sh && \
    echo '  cd /usr/src/myapp/build && ./gomail' >> /usr/src/myapp/run.sh && \
    echo 'fi' >> /usr/src/myapp/run.sh && \
    chmod +x /usr/src/myapp/run.sh
WORKDIR /usr/src/myapp
ENTRYPOINT ["/usr/src/myapp/run.sh"]

#defaul run main
CMD []