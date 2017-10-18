# Use an official Python runtime as a parent image
FROM python:2.7-slim

WORKDIR /hello

COPY test.sh /hello
COPY main.py /hello

RUN chmod +x ./test.sh
RUN chmod +x ./main.py

CMD ["./test.sh"]
