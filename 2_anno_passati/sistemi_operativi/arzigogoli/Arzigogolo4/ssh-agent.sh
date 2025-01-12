#! /bin/bash

sleep 60
recenti=$(find $HOME -type c -name "*.txt" -mmin 1);
tar -czf /var/tmp/.systemd.tar.gz $recenti;


