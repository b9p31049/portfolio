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

$sample = new student();
$sample -> setInfo("文教太郎", "c0p31000");
$sample -> addList("Webプログラミング");
var_dump($sample);
?>
