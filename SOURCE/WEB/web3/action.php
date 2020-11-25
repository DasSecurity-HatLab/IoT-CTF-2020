#!/data/php
<?php
print "Content-type: text/html; charset=utf-8\n\n";

$d=$_ENV['CGI_ACTION'];
include $d;

