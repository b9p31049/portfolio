<!doctype html>
<html lang="ja">
<head>
    <meta charset="utf-8">
    <title>セッション</title>
</head>
<body>
    <h1>セッション</h1>
    <form method="post" action="ex7-1a.php">
        設定する値：<input name="s"><br>
        <input type="submit" value="設定">
    </form>
<?php

if(isset($_POST["s"])){
    session_start();
    $_SESSION["sample"] = $_POST["s"];
    echo("<p>セッションに値が設定されました</p>");
}

?>
    <hr>
    <p><a href="ex7-1a.php">セッションに値を設定</a></p>
    <p><a href="ex7-1b.php">セッションの値を確認</a></p>
    <p><a href="ex7-1c.php">セッションの値を破棄</a></p>
</body>
</html>
