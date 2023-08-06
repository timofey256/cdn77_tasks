# unpack source
gunzip ./nginx-1.25.1.tar.gz
tar -xvf ./nginx-1.25.1.tar

cd nginx-1.25.1

# patch code
patch src/http/ngx_http_upstream.c ../ngx_http_upstream.diff

# compile source
sudo ./configure --prefix=../nginx --modules-path=../nginx/modules --with-http_ssl_module  --without-http_fastcgi_module --without-http_uwsgi_module --without-http_grpc_module --without-http_scgi_module --without-mail_imap_module --without-mail_pop3_module
sudo make
sudo make install

cd ..

# copy config and proxy_params (tbh, idk why it isn't in source. maybe there should a specific flag in ./configure)
sudo cp ./nginx.conf ./nginx/conf/
sudo cp ./proxy_params ./nginx/conf/

# run server
cd nginx
sudo sbin/nginx -c conf/nginx.conf
