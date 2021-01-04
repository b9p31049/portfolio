<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>データベース</title>
</head>
<body>
    <h1>データベース</h1>
    <hr>
    <form method="post" action="ex12-1c.php">
<?php
$html  = "授業名：<input name='授業名' value='{$_POST["授業名"]}'><br>";
$html .= "教　員：<input name='教員' value='{$_POST["教員"]}'><br>";
$html .= "曜　日：<input name='曜日' value='{$_POST["曜日"]}'><br>";
$html .= "時　間：<input name='時間' value='{$_POST["時間"]}'><br>";
$html .= "<input type='hidden' name='更新前授業名' value='{$_POST["授業名"]}'>";
$html .= "<input type='hidden' name='更新前教員' value='{$_POST["教員"]}'>";
$html .= "<input type='hidden' name='更新前曜日' value='{$_POST["曜日"]}'>";
$html .= "<input type='hidden' name='更新前時間' value='{$_POST["時間"]}'>";
echo($html);
?>
        <input type="submit" value="更新">
    </form>
</body>
</html>
