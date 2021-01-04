<?php
$v1 = 10 == 10; $v2 = 10 === (string)10; 
$v3 = 10 > 10; $v4 = 10 >= 10; 
$v5 = 10 < 10; $v6 = 10 <= 10; 
$v7 = 10 != 10; $v8 = 10 !== (string)10;

echo("{$v1}のデータ型は，「" . gettype($v1) . "」です<br>"); 
echo("{$v2}のデータ型は，「" . gettype($v2) . "」です<br>"); 
echo("{$v3}のデータ型は，「" . gettype($v3) . "」です<br>"); 
echo("{$v4}のデータ型は，「" . gettype($v4) . "」です<br>"); 
echo("{$v5}のデータ型は，「" . gettype($v5) . "」です<br>"); 
echo("{$v6}のデータ型は，「" . gettype($v6) . "」です<br>"); 
echo("{$v7}のデータ型は，「" . gettype($v7) . "」です<br>"); 
echo("{$v8}のデータ型は，「" . gettype($v8) . "」です<br>");
?>
