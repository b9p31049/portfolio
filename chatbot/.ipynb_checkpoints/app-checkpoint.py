from flask import Flask, request, abort

from linebot import (
    LineBotApi, WebhookHandler
)
from linebot.exceptions import (
    InvalidSignatureError
)
from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage,
)

app = Flask(__name__)

line_bot_api = LineBotApi('yP0cYOerBzGG4dVeXGpajl/apFmGKFmq90y9QxrEDuQu5s3A5JNpl/WUgQCeh19MC7TFgIQWDnBJGyxx/V8byY8rsJgOYSH3ET0mzhGoT6zOzGAAWEq8+N1bxNZw3MvBgIJWkMOdRqcOgY4nh7bh5QdB04t89/1O/w1cDnyilFU=')
handler = WebhookHandler('15587575c00782e63a5dc56da76837f6')

@app.route("/")
def  test():
    return "OK"


@app.route("/callback", methods=['POST'])
def callback():
    # get X-Line-Signature header value
    signature = request.headers['X-Line-Signature']

    # get request body as text
    body = request.get_data(as_text=True)
    app.logger.info("Request body: " + body)

    # handle webhook body
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        print("Invalid signature. Please check your channel access token/channel secret.")
        abort(400)

    return 'OK'


@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    if event.message.text == "あなたは誰？":
        line_bot_api.reply_message(
            event.reply_token,
            TextSendMessage(text="おらしゅんくんだよ"))

    elif event.message.text == "好きな人だれ？":
        line_bot_api.reply_message(
            event.reply_token,
            TextSendMessage(text="ゆりなちゃん！"))

    elif event.message.text == "今日も生きててえらい？":
        line_bot_api.reply_message(
            event.reply_token,
            TextSendMessage(text="偉いね　明日も俺と一緒に生きようね"))
    else:
        line_bot_api.reply_message(
            event.reply_token,
            TextSendMessage(text=event.message.text))


if __name__ == "__main__":
    app.run()