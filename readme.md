# 机房预约系统

为了防止学生用电脑”撞车“。

## 系统中的身份信息

1. 学生代表：申请机房
2. 教师：审核学生的预约信息
3. 管理员：给学生、教师创建账号

## 机房简介

* 1号机房 -- 最大容量20人
* 2号机房 -- 最多容量50人
* 3号机房 -- 最多容量100人

## 申请简介

* 申请订单每周由管理员负责清空
* 学生可以申请一周内的机房使用，预约的日期为周一至周五，预约时需要选择预约时间段（上午、下午）
* 教师来审核预约，依据实际情况审核预约是否通过

## 系统具体需求

* 首先进入登录界面，可选择登录身份
  - 学生需要输入: 学号、姓名、登录密码
  - 老师需要输入：职工号、姓名、登录密码
  - 管理员需要输入：管理员姓名、登录密码
* 学生具体功能
  - 预约申请 -- 预约机房
  - 查看自身的预约 -- 查看自己的预约状态
  - 查看所有预约 -- 查看所有预约信息以及预约状态
  - 取消预约 -- 取消自身预约，预约成功或者审核中的预约均可取消
  - 注销登录
* 教师具体功能
  - 查看所有预约 -- 查看所有预约信息以及预约状态
  - 审核预约 -- 对学生的预约进行审核
  - 注销登录
* 管理员具体功能
  - 添加账号 -- 添加学生或教师账号，需要检测学生编号或者教师工号是否重复
  - 查看账号 -- 可以选择查看学生或教师的全部信息
  - 查看机房 -- 查看所有机房信息
  - 清空预约 -- 清空所有预约记录
  - 注销登录
