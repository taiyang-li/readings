#!/usr/bin/python
#encoding:utf-8

import logging
import logging.handlers
import sys
import os

def _file_name_gen(prog_name, log_dir, is_error_log=False):
    """
    Generate filename from program name
    """
    if log_dir.endswith('/'):
        # remove the last '/'
        log_dir = log_dir[0:-1]

    if is_error_log:
        # warning, error, critical
        file_name = os.path.join(log_dir, prog_name + ".wf.log")
    else:
        # all log
        file_name = os.path.join(log_dir, prog_name + ".log")

    return file_name


def _logdir_check_create(dir_path):
    """
    check, and create dir if nonexist
    """
    ret_val = 'OK'

    if not os.path.exists(dir_path):
        try:
            # create directory (recursively)
            os.makedirs(dir_path)
        except OSError:
            ret_val = 'ERROR'

    return ret_val


def log_init(prog_name, log_dir, log_level=logging.DEBUG, format_str=None,
            when='D', backup_count=7, stdout=True):
    """
    init log and create files prog_name.log and prog_name.wf.log.
    """
    # check, and create dir if nonexist
    if _logdir_check_create(log_dir) != 'OK':
        logging.error("logInit(), in _logdir_check_create(%s)" % log_dir)
        return "ERROR"

    # set log file name
    _log_file_name = _file_name_gen(prog_name, log_dir)
    # warning and fatal
    _log_wf_fileName = _file_name_gen(prog_name, log_dir, True)

    # set format
    if format_str is None:
        format_str = ('%(asctime)s [%(levelname)s][%(filename)s:%(lineno)s]:'
                     ' %(message)s')
    formatter = logging.Formatter(format_str)

    logger = logging.getLogger()
    # root logger is created with level WARNING, modify it
    logger.setLevel(log_level)

    # prepare handler for file rotate, all log
    log_handler = logging.handlers.TimedRotatingFileHandler(
                    _log_file_name, when=when, backupCount=backup_count)
    log_handler.setLevel(log_level)
    log_handler.setFormatter(formatter)
    logger.addHandler(log_handler)

    # prepare handler for file rotate, > WARNING
    log_handler = logging.handlers.TimedRotatingFileHandler(
                    _log_wf_fileName, when=when, backupCount=backup_count)
    log_handler.setLevel(logging.WARNING)
    log_handler.setFormatter(formatter)
    logger.addHandler(log_handler)

    # prepare handler for stdout
    if stdout:
        log_handler = logging.StreamHandler()
        log_handler.setLevel(log_level)
        log_handler.setFormatter(formatter)
        logger.addHandler(log_handler)

    return "OK"
