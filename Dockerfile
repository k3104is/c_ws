FROM alpine:latest

RUN sed -i 's/https/http/' /etc/apk/repositories

RUN apk add --no-cache gcc libc-dev \
  alpine-sdk cmake clang libressl-dev \
  vim 
