<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>クラス</title>
</head>
<body>
    <h1>クラス</h1>

<table>
<table border="1">


<?php

class student{

//プロパティ
var $name; //名前
var $no; //学籍番号
var $slist; //履修科目リスト

//メソッド
function __construct(){
$this -> slist = array();
}

function setInfo($name, $no){
$this -> name = $name;
$this -> no = $no;
}

function addList($name){
$this -> slist[] = $name;
}

}


class jugyo{
    var $name; //授業名
    var $kyoin; //教員名
    var $jikan; //時間
    var $youbi; //曜日
    function __construct($name, $kyoin, $jikan, $youbi){
    $this -> name = $name;
    $this -> kyoin = $kyoin;
    $this -> jikan = $jikan;
    $this -> youbi = $youbi;
    }
    }



$sample = new student();
$sample -> setInfo("文教太郎", "c0p31000");
$sample -> addList(new jugyo("Webプログラミング", "池辺", 2, "木"));
$sample -> addList(new jugyo("Webプログラミング応用", "池辺", 2, "火"));
echo("<td>");
var_dump($array[1]);
echo("</td>");
?>

</table>

</body>
</html>