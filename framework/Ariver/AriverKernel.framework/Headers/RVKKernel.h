//
//  RVKKernel.h
//  Poseidon
//
//  Created by chenwenhong on 14/7/17.
//  Copyright (c) 2014年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RVKEventTargetProtocol.h"
#import "RVKExpandoProtocol.h"
#import "RVKEvent.h"


#define RVK_DEFINE_FUNCTION(returnType, var)              \
- (id)var                                                 \
{                                                         \
    if (_##var == nil) {                                  \
        _##var = [[returnType alloc] init];               \
    }                                                     \
    return _##var;                                        \
}

#define RVK_ASSERT(condition) \
if (!condition) {\
    NSString *reason = [NSString stringWithFormat:@"\n\n***********************************************************\nPOSEIDON内核抛出的断言（Kernel Assert）:\n函数:%s-%d \ncondition=%s\n\n", __FUNCTION__, __LINE__, #condition];\
    NSLog(@"%@",reason);\
}

#define RVK_ASSERT2(condition, desc) \
if (!condition) {\
    NSString *reason = [NSString stringWithFormat:@"\n\n***********************************************************\nPOSEIDON内核抛出的断言（Kernel Assert）:\n函数:%s-%d \ncondition=%s desc=%@\n\n", __FUNCTION__, __LINE__, #condition, desc];\
    NSLog(@"%@", reason);\
}

@class RVKJsApiManager;
@class RVKPluginManager;
@class RVKExtensionNodeRegistry;

//内核对象
@interface RVKKernel : NSObject <RVKEventTargetProtocol, RVKExpandoProtocol>

/**
 *  @brief 获取jsApi管理实例
 *
 *  @date 2015-08-14
 *
 *  @return 返回jsApi管理实例
 */
- (RVKJsApiManager *)jsApiManager;

/**
 *  @brief 获取plugin管理实例
 *
 *  @date 2015-08-14
 *
 *  @return 返回plugin管理实例
 */
- (RVKPluginManager *)pluginManager;

- (RVKExtensionNodeRegistry *)extensionManager;

/**
 *  @brief 返回父节点对象
 *
 *  @date 2014-08-20
 *
 *  @return 返回父节点对象
 */
- (RVKKernel *)parentKernelObject;

/**
 *  @brief 添加一个子节点对象
 *
 *  @date 2014-08-20
 *
 *  @param object 子节点对象
 *
 *  @return 无
 */
- (void)addSubObject:(RVKKernel *)object;

/**
 *  @brief 移除一个子节点对象
 *
 *  @date 2014-08-20
 *
 *  @param object 子节点对象
 *
 *  @return 无
 */
- (void)removeSubObject:(RVKKernel *)object;

/**
 *  @brief 移除第一个子节点
 *
 *  @date 2015-08-14
 *
 *  @return 无
 */
- (void)removeFirstSubObject;

/**
 *  @brief 移除最后一个子节点
 *
 *  @date 2015-08-14
 *
 *  @return 无
 */
- (void)removeLastSubObject;

/**
 *  @brief 从父节点移除
 *
 *  @date 2014-08-20
 *
 *  @return 无
 */
- (void)removeFromSuperObject;

/**
 *  @brief 返回所有子节点对象数组
 *
 *  @date 2014-08-20
 *
 *  @return 返回所有子节点对象数组
 */
- (NSArray *)subObjects;

/**
 *  @brief 获取第一个子节点
 *
 *  @date 2015-08-14
 *
 *  @return 返回第一个子节点
 */
- (RVKKernel *)firstSubObject;

/**
 *  @brief 获取最后一个子节点
 *
 *  @date 2015-08-14
 *
 *  @return 返回最后一个子节点
 */
- (RVKKernel *)lastSubObject;

/**
 *  @brief 返回唯一id
 *
 *  @date 2014-08-20
 *
 *  @return 返回唯一id
 */
- (NSString *)uniqueId;

/**
 *  分发消息给当前的EventTarget对象
 *
 *  @param event RVKEvent类型的事件对象
 *
 *  @return 如果事件处理过程中，有target调用了preventDefault，就返回NO
 */
- (BOOL)dispatchEvent:(RVKEvent *)event;

/**
 *   定义结点scope，默认返回scope-undefined
 */
- (NSString *)scope;


@end
