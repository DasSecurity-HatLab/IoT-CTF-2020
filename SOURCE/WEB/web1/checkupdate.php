#!/data/php
<?php

session_start();

print "Content-type: text/html; charset=utf-8\n\n";
if(empty($_SESSION['name'])){
    echo "login first";
    //exit();
    //whataver  just do it lucky guy
}
$url =$_ENV['CGI_URL'];


$cmd = "curl http://x11router.com/".$url." -o /tmp/test.bin ";
$cmd = escapeshellcmd($cmd);
#echo $cmd."\n";
shell_exec($cmd);
echo "Done";


//when we can't unpack the firmware or no firmware, we usually pentest to get shell first.
//hint : do u know rpc on this server ? get root shell
