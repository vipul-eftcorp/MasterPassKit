//
//  MPPayByCard.h
//  MasterPassKit
//
//  Created by Vipul Patel on 15/07/24.
//  Copyright © 2024 Mobilica (Pty) Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPPayByCardDelegate <NSObject>
- (void)didPayByCardTapped;
@end

@interface MPPayByCard : UIView
@property (strong, nonatomic) id<MPPayByCardDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
