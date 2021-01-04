<?php

class student{
    var $name;
    var $no;
    var $mail;
    function __construct($arr){
        foreach($arr as $k => $v) $this -> $k = $v;
    }
}

class jugyo{
    var $slist;
    var $name;
    function __construct(){
        $this -> name = "Webプログラミング";
        $this -> slist = array();
    }

    function addStudent($arr){
        $this->slist[] = new student($arr);
    }

    function getInfo(){
        $html = "授業名：{$this->name}の履修者リスト<hr><ol>";
        foreach($this->slist as $k => $v) $html .= "<li>{$v->name} / {$v->no} / {$v->mail}</li>";
        $html .= "</ol>";
        return($html);
        }
    }
    
?>