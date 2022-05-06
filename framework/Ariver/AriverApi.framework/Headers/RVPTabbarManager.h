//
//  RVPTabBarManager.h
//  NebulaBiz
//
//  Created by lyusheng on 2019/1/16.
//  Copyright © 2019 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RVPVCTabBarProtocol.h"
#import <AriverApp/RVATabBarProtocol.h>

NS_ASSUME_NONNULL_BEGIN

#define kH5TabBarJsonConfigDict @"kH5TabBarJsonConfigDict"
#define kH5TabBarShouldCreateTabAfterSession @"kH5TabBarShouldCreateTabAfterSession"
#define kH5TabBarSelectTabIndexAfterSession @"kH5TabBarSelectTabIndexAfterSession"
#define kH5TabBarShouldCreateFakeTabAfterSession @"kH5TabBarShouldCreateFakeTabAfterSession"
#define kH5TabBarShouldCreateFakeTabItemCount @"kH5TabBarShouldCreateFakeTabItemCount"
#define kDefaultTabBarHeight                  49

@interface RVPTabBarManager : NSObject<RVATabBarProtocol>

@property (nonatomic, assign) BOOL associated;

// implementation of RVATabBarProtocol
/*---------------------------------------------------------------*/
 /**
 用于占位的tabBar
 */
@property(nonatomic, strong, nullable) UITabBar *placeholderTabBar;
/**
 自定义TabBarController, tabBar控件
 */
@property(nonatomic) UITabBar *tabBar;

/**
 缓存tabBar未创建前的tabBar操作指令
 */
@property(nonatomic, readonly)  NSMutableArray<void (^)() >* delayTabBarTasks;

/**
 是否持有多Tab的其它子Tab
 */
@property(nonatomic, readonly) BOOL hasChildTab;

/**
 是否为多Tab的子Tab
 */
@property(nonatomic) BOOL isChildTab;

/**
 多Tab时，是否可见
 */
@property(nonatomic, readonly) BOOL isNotVisibleWhenMultiTab;

/**
 是否需要停止手动补齐appearance事件
 */
@property(nonatomic, assign) BOOL stopConstructAppearance;

/**
 持有的子Tab的数目
 */
@property(nonatomic, readonly) NSUInteger childTabCount;

/**
 设置/读取选中tag
 */
@property(nonatomic) NSString *selectedTag;

/**
 作为子Tab被执有的H5WebViewController
 */
@property(nonatomic, weak) UIViewController *cachedParentViewController;

/**
 多tab模式时，返回兄弟tab里选中的的H5WebViewController
 非tab模式时，直接返回调用的H5WebViewController
 */
@property(nonatomic, readonly) UIViewController *selectedViewController;

/**
 持有创建的子Tab对应的H5WebViewController
 键值对中，键名为对应Tab的identifier
 */
@property(nonatomic, strong) NSDictionary<NSString *, UIViewController *> *cachedChildViewControllers;

@property(nonatomic, assign) BOOL hasAlphaBackgroundColor;
/*---------------------------------------------------------------*/


// vc safearea 变更回调，同步给 tabbar
- (void)viewSafeAreaInsetsDidChange;
@end

@interface RVPTabBarManager(apis)

- (UIViewController *)childTabViewController;
- (instancetype)initWithViewController:(UIViewController *)vc;
- (void)associateToViewController:(UIViewController *)vc;
@end

NS_ASSUME_NONNULL_END
