 #define MAX_SIZE 80


void download(char *repertory, char *file){
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {
    file, /* name to store the file as if successful */ 
    NULL
  };
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works!
     */ 
    curl_easy_setopt(curl, CURLOPT_URL,
                     repertory);                 
    /* Define our callback to get called when there's data to be written */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */ 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 
    /* Switch on full protocol/debug output */ 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
 
    res = curl_easy_perform(curl);
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    if(CURLE_OK != res) {
      /* we failed */ 
      fprintf(stderr, "curl told us %d\n", res);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */ 
 
  curl_global_cleanup();
} 