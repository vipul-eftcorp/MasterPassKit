//
//  MPPayByApp.h
//  MasterPassKit
//
//  Created by Vipul Patel on 17/07/24.
//  Copyright © 2024 Mobilica (Pty) Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPPayByAppDelegate <NSObject>
- (void)didPayByAppWithInfo:(nullable NSDictionary *)appInfo;
@end

@interface MPPayByApp : UIView
@property (strong, nonatomic) id<MPPayByAppDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
