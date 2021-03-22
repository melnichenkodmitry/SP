FROM debian
WORKDIR /home/dimam/SP
COPY . .
RUN chmod +x script.sh && ./script.sh
