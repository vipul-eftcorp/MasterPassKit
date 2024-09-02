//
//  MPParentViewController.h
//  MasterPassKit
//
//  Created by Vipul Patel on 30/05/24.
//  Copyright © 2024 Mobilica (Pty) Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum {
    PRODUCT_SCREEN = 0,
    ADD_SCREEN = 1,
    CARDS_SCREEN = 2,
} BACK_TO_SCREEN ;

@interface MPParentViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIView *viewMain;
@property (weak, nonatomic) IBOutlet UIView *viewModal;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *constraintHeightViewModal;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *constraintBottomViewModal;
@property (weak, nonatomic) IBOutlet UIView *viewNavigationBar;
@property (weak, nonatomic) IBOutlet UIButton *btnClose;
@property (weak, nonatomic) IBOutlet UIStackView *stackViewBranding;
@property (weak, nonatomic) IBOutlet UILabel *lblPoweredBy;
@property (weak, nonatomic) IBOutlet UIImageView *imgVwBranding;
@property (weak, nonatomic) IBOutlet UIView *viewBottomLayout;
@property (nonatomic) BACK_TO_SCREEN backToScreen;

- (void)initUIs;
- (void)initNavigationBarUIs;
- (void)updateUIsBasedOnTheme;
- (void)registerKeyboardNotification;
- (IBAction)onButtonClosePress:(UIButton *)sender;

@end

NS_ASSUME_NONNULL_END
