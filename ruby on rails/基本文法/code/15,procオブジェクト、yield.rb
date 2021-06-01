# proc → to end や　{}　を オブジェクト化したもの

    # procの作成
    proc = Proc.new { puts 'hoge ' }
    proc.class

    # 呼び出し
    proc.call

    # あらかじめ変数を定義していることで、procの中身も変数を参照することができる。


# yeild →　メソッド呼び出しで、メソッドの中で実行

    def yeild_test
        yeild(1, 2)
    end

    puts yeild_test { |a, b| a + b }


