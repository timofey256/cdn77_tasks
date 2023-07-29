mkdir -p logs

PATH=/usr/local/openresty/nginx/sbin:$PATH
export PATH

nginx -s reload -p `pwd`/ -c conf/nginx.conf
