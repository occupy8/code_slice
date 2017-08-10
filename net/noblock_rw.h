/**
* @fn readx
* @brief readx "n" bytes to a descriptor,should be set Noblock outide.
* @param[in]  fd   : file descriptor
* @param[in]  vptr : buffer to be read, allocated by caller  
* @param[in]  buf_len    : maximum bytes to be read
* @return  the result of function. success or fail;
* @retval  -1 :  read error
* @retval   n :  n bytes are gotten
* @retval  <n :  '<n' bytes are gotten, but socket closed or file ended.
*/
int readx( int sock, char* buf, int buf_len )
{
     int  left;
     int  n;
     char  *ptr = NULL;

     ptr = (char*)buf;
     left = buf_len;

     while( left > 0 )
     {
          if( (n = read( sock, ptr, left) ) < 0)
          {
               if (EINTR == errno)
               {
                    continue;
               }

               if( errno == EAGAIN )
               {
                    break;
               }
               else
               {
                    return (-1);
               }
          }
          else if (0 == n)
          {
               return (-1);
          }

          left -= n;
          ptr += n;
          break;

     }

     return (buf_len - left);
}

int writex( int sock, char* buf, int buf_len )
{
     int  left;
     int  n;
     char  *ptr = NULL;

     ptr = (char*)buf;
     left = buf_len;

     while( left > 0 )
     {
          if( (n = write( sock, ptr, left) ) < 0)
          {
               if (EINTR == errno)
               {
                    continue;
               }

               if( errno == EAGAIN )
               {
                    break;
               }
               else
               {
                    return (-1);
               }
          }
          else if (0 == n)
          {
               return (-1);
          }

          left -= n;
          ptr += n;
          break;

     }

     return (buf_len - left);
}
