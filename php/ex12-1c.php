<?php
if(isset($_POST["授業名"], $_POST["教員"], $_POST["曜日"], $_POST["時間"], $_POST["更新前授業名"], $_POST["更新前教員"], $_POST["更新前曜日"], $_POST["更新前時間"])){
    $arr = array($_POST["授業名"], $_POST["教員"], $_POST["曜日"], $_POST["時間"], $_POST["更新前授業名"], $_POST["更新前教員"], $_POST["更新前曜日"], $_POST["更新前時間"]);
    $dsn = "mysql:dbname=sample01;host=localhost";
    $my = new PDO($dsn, "wp", "wp");
    $sql = "UPDATE 授業 SET 授業名=?, 教員=?, 曜日=?, 時間=? WHERE 授業名=? AND 教員=? AND 曜日=? AND 時間=?;";
    $st = $my->prepare($sql);
    $st->execute($arr);
    header("location:ex12-1.php");
}

?>
