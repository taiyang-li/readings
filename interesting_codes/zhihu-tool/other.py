#!/usr/bin/env python
# coding: utf-8
import os
from zhihu_oauth import ZhihuClient, ActType, People
from zhihu_oauth.exception import NeedCaptchaException
from zhihu_oauth.helpers import ts2str, act2str

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

def dump_activities(pid):
    person = client.people(pid)
    filter_types = {
            ActType.COLLECT_ANSWER,
            ActType.COLLECT_ANSWER,
            ActType.COLLECT_ARTICLE,
            ActType.CREATE_ANSWER,
            ActType.CREATE_ARTICLE,
            ActType.CREATE_PIN,
            ActType.CREATE_QUESTION,
            ActType.FOLLOW_COLLECTION,
            ActType.FOLLOW_COLUMN,
            ActType.FOLLOW_QUESTION,
            ActType.FOLLOW_ROUNDTABLE,
            ActType.FOLLOW_TOPIC,
            ActType.LIKE_PIN,
            ActType.JOIN_LIVE,
            ActType.PUBLISH_LIVE,
            ActType.VOTEUP_ANSWER,
            ActType.VOTEUP_ARTICLE,
            ActType.VOTEUP_EBOOK,
    }
    ret = []
    for act in person.activities.filter(filter_types):
        ret.append("%s | %s" % (ts2str(act.created_time), act2str(act).encode('utf-8')))
    return sorted(ret)

def batch_dump_activities(pids):
    ret = {}
    if len(pids) == 0:
        return ret

    for pid in pids:
        ret[pid] = dump_activities(pid)
    return ret

pids = ['your-pid']
activities_by_pid = batch_dump_activities(pids)
for pid in activities_by_pid:
    print "pid:%s" % (pid)
    for act in activities_by_pid[pid]:
        print "\t\t%s" % (act)
