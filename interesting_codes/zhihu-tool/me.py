#!/usr/bin/env python
# coding: utf-8
import os
from zhihu_oauth import ZhihuClient, ActType
from zhihu_oauth.exception import NeedCaptchaException

token = './XXX.pk1'
client = ZhihuClient()

try:
    if os.path.exists(token):
        client.load_token(token)
    else:
        client.login('username', 'passwd')
except NeedCaptchaException:
    # 保存验证码并提示输入，重新登录
    with open('a.gif', 'wb') as f:
        f.write(client.get_captcha())
    captcha = raw_input('please input captcha:')
    client.login('username', 'passwd', captcha)

client.save_token(token)

# show user status 
me = client.me()
print('name', me.name)
print('headline', me.headline)
print('description', me.description)

print('following topic count', me.following_topic_count)
print('following people count', me.following_count)
print('followers count', me.follower_count)

print('voteup count', me.voteup_count)
print('get thanks count', me.thanked_count)

print('answered question', me.answer_count)
print('question asked', me.question_count)
print('collection count', me.collection_count)
print('article count', me.articles_count)
print('following column count', me.following_column_count)

# show other activities
for act in me.activities:
    if act.type == ActType.CREATE_ANSWER:
        print(act.target.question.title)
