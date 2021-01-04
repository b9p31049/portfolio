<?php

$n = $_POST["n"]; 

if($n < 0 || $n > 100){
    echo("エラー");
}
else if($n < 60){
    echo("D判定");
}
else if($n < 70){
    echo("C判定");
}
else if($n < 80){
    echo("B判定");
}
else if($n < 90){
    echo("A判定");
}
else{
    echo("AA判定");
}
    
?>