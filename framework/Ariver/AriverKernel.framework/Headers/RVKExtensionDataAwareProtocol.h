//
//  RVKExtensionDataAwareProtocol.h
//  NebulaKernel
//
//  Created by theone on 2018/8/26.
//  Copyright © 2018年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
@protocol RVKExtensionDataStorageProtocol;

@protocol RVKExtensionDataAwareProtocol <NSObject>
@optional
- (Class)dataTypeClass;
- (void)setDataStorage:(id<RVKExtensionDataStorageProtocol>)dataStorage;
@end
