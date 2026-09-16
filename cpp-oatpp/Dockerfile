FROM ubuntu:24.04 AS builder

ARG OATPP_COMMIT=f83d648fd82dc222ef88aabbafb68efbd7d7bf50

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        cmake \
        git \
    && rm -rf /var/lib/apt/lists/*

RUN git init /tmp/oatpp \
    && git -C /tmp/oatpp remote add origin https://github.com/oatpp/oatpp.git \
    && git -C /tmp/oatpp fetch --depth 1 origin "${OATPP_COMMIT}" \
    && git -C /tmp/oatpp checkout --detach FETCH_HEAD \
    && cmake -S /tmp/oatpp -B /tmp/oatpp/build \
        -DCMAKE_BUILD_TYPE=Release \
        -DOATPP_BUILD_TESTS=OFF \
        -DOATPP_INSTALL=ON \
    && cmake --build /tmp/oatpp/build --parallel \
    && cmake --install /tmp/oatpp/build

WORKDIR /app
COPY . .

RUN cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_PREFIX_PATH=/usr/local \
    && cmake --build build --target cpp-api --parallel

FROM ubuntu:24.04 AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        libatomic1 \
        libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/cpp-api ./cpp-api

EXPOSE 8000

CMD ["./cpp-api"]
