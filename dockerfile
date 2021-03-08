FROM debian
COPY lab1.sh .
RUN chmod ugo+x lab1.sh
CMD ./lab1.sh
