# クラスメソッド、クラス変数

# クラスメソッドの定義
class Foo
    # ❶　メソッド名の頭にselfをつける
    def self.first_method
        puts 'first'
    end

    # ❷まとめてクラスメソッドにする場合
    class << self
        def second_method
            puts 'second'
        end

        def third_method
            puts 'third'
        end
    end
end

Foo.first_method
Foo.second_method
Foo.third_method

# ※オブジェクトから呼び出すことはできない


# クラス変数について

class Num
    @@num = 1

    def increment
        @@num += 1
    end

    def decrement
        @@num -= 1
    end

    def num
        puts @@num
    end

    def self.num
        puts @@num
    end
end

foo = Num.new
foo.num
foo.increment
foo.num
    
bar = Num.new
bar.num
bar.increment
bar.num
bar.decrement
bar.num

# 保存されている