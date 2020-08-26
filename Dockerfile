FROM gcc:10 AS build

# Change dir and copy files
WORKDIR /shipyard
COPY src/ src/
COPY Makefile .

# Build static library
RUN make

# Set up env vars and change dir for child images
ENV SRC_DIR /shipyard/src
ENV LIB_DIR /shipyard/build
ENV LIB_NAME shipyard
WORKDIR /task
