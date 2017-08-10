static int conn_nonb(int sockfd, struct sockaddr *saptr, int salen, int nsec)  
{  
        int flags, n, error, code;  
        socklen_t len;  
        fd_set wset;  
        struct timeval tval;  

        flags = fcntl(sockfd, F_GETFL, 0);  
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);	

        error = 0;	
        if ((n = connect(sockfd, saptr, salen)) == 0) {  
                goto done;	
        } else if (n < 0 && errno != EINPROGRESS){	
                return (-1);  
        }  

        /* Do whatever we want while the connect is taking place */
        FD_ZERO(&wset);  
        FD_SET(sockfd, &wset);	
        tval.tv_sec = nsec;  
        tval.tv_usec = 0;  

        if ((n = select(sockfd+1, NULL, &wset, NULL, nsec ? &tval : NULL)) == 0) {  
                close(sockfd);	/* timeout */  
                errno = ETIMEDOUT;	
                return (-1);  
        }  

        if (FD_ISSET(sockfd, &wset)) {	
                len = sizeof(error);  
                code = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);	
                if (code < 0 || error) {  
                        close(sockfd);	
                        if (error)	 
                              errno = error;	
                        return (-1);  
                }  
        } else {  
                fprintf(stderr, "select error: sockfd not set"); 
                return -1;  
        }  

done:  
        fcntl(sockfd, F_SETFL, flags);	/* restore file status flags */  
        return (0);  
}  
