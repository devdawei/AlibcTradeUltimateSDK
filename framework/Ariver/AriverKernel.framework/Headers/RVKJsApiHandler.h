//
//  RVKJsApiHandler.h
//  Poseidon
//
//  Created by chenwenhong on 14-8-20.
//  Copyright (c) 2014年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RVKJsApi.h"

//通用错误回调 
void RVKErrorCallback(RVKJsApiResponseCallbackBlock callback, int code);

//通用错误码
#define e_invalid_api           1   //无效的api接口
#define e_inavlid_params        2   //无效的api入参
#define e_unknown_error         3   //未知错误
#define e_permission_denied     4   //无权调用该接口

#define e_user_cancel           11  //用户取消操作

#define RVK_CALLBACK_TYPE_INFO              @"NEBULATYPEINFO"
#define RVK_CALLBACK_KEY_OF_TYPE            @"type"
#define RVK_CALLBACK_TYPE_ARRAYBUFFER       @"ArrayBuffer"



@class RVKContext;

//JsApi处理类（基类）
@interface RVKJsApiHandler : NSObject
/**
 *  @brief JsApi处理函数
 *
 *  @date 2014-08-20
 *
 *  @param data     处理的内容
 *  @param context  当前上下文信息
 *  @param callback 回调
 *
 *  @return 无
 */
- (void)handler:(NSDictionary *)data context:(RVKContext *)context callback:(RVKJsApiResponseCallbackBlock)callback;

@end
