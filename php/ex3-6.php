<!doctype html> <html lang="ja"> 
<head> 
    <meta charset="utf-8"> 
    <title>関数</title> 
</head> 
<body> 
    <h1>関数</h1> 
<?php

//関数sampleを作成します 
function sample($arg1, $arg2){ 
    $result = "<p>関数sampleが呼び出されました．"; 
    $result .= "受け取った引数は{$arg1}と{$arg2}です</p>"; 
    return($result); 
}

//関数sampleを呼び出して変数htmlに結果を保持 
$html = sample("Webプログラミング", 1000);

echo($html);
?>
 </body> 
 </html>
