# クラスにおけるメソッド定義

# インスタンス変数(@)
require 'date'

class User
    attr_accessor :name, :birthday

    def initialize(name, birthday)
        @name = name
        @birthday = birthday
    end

    def display_birthday
        @birthday.strftime('%Y年 %m月 %d日')
    end

    def inner_call_display_birthday
        self.display_birthday
        display_birthday
    end

    def call_private_name
        private_name
    end

    private

    def private_name
        @name
    end
end

birthday = Date.new(2000, 8, 1)
user = User.new('yurina', birthday)
puts user.call_private_name


# 三種類
    # publicメソッド(どこでも開ける)
    # self メソッド(自分のクラスないのメソッドの呼び出し)
    # privateメソッド(クラス外部には公開されない)


    # よく使うもの
        %w[a b c].include('c')
        # true

        %w[a b c].include('d')
        # false