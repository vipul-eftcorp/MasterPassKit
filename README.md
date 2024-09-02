# Introduction

Scan to Pay In-App payments is a library supplied by ~~UKheshe South Africa (previously Oltio Pty Ltd)~~ to 3rd party app developers who require in-app purchases. To use the library, a merchant account has to be set up using the Scan to Pay SA system.

The 3rd Party developer must be familiar with creating a code and getting notified of the payment. These can be found in the Scan to Pay API for Secure MOTO and Face-to-Face documents.

The library is released as a Cocoa Touch Framework, called Scan to PayKit.Framework. The following environments are currently supported:

## Operating system

- iOS 12+

## Languages

- Swift
- Objective-C

## Add the Scan to PayKit Framework to Your Project

Go to your project target settings and select the General tab. Click the + sign under Embedded Binaries. Click the Add Other button and navigate to the provided Scan to PayKit.framework. Select “Copy items if needed” and “Create Groups” when prompted.

![alt text](./Documents/Add_the_Scan_to_PayKit_Framework_to_Your_Project.png "Add the Scan to PayKit Framework to Your Project")

## Set the Location Usage Description

Open your “Info.plist” file. Add a new key called “NSLocationWhenInUseUsageDescription” with type String  
and appropriate value, for example, “Your location will be used to prevent fraud”.

![alt text](./Documents/Set_the_Location_Usage_Description.png "Set the Location Usage Description")

## Requesting a Payment

The following steps summarize an in-app payment request:

- 3rd party backend uses the Scan to Pay API to create a transaction code (which contains the amount, references, etc.).
- The 3rd party app calls Scan to PayKit, passing in this newly created code.
- The Scan to Pay in-app library will facilitate the payment and call a delegate method to return a result and reference indicating the payment status.
- The 3rd  backend will then query the Scan to Pay system with the returned reference to guarantee the payment status. Alternatively, the 3rd  backend will query itself to see if Scan to Pay has notified it of a new payment.

> 📘 Note
>
> It is imperative that the 3rd party app does not trust the library's result as the final status. A backend API call must be done to verify the payment status from the notification.

## Calling the Checkout Method

The following snippet illustrates how to invoke the payment request from Swift:

```
import MasterPassKit

@IBAction func checkoutAction(sender: AnyObject) {
    
    let code = "6799782555"
    let apiKey = "1234567890"
    let system = MPSystem.test

    let masterpass = MPMasterPass();
    masterpass.checkout(withCode: code!, apiKey: apiKey, system: system, controller: self, delegate: self)

    //or

    let preMsisdn = "27123456789"
    masterpass.checkout(withCode: code, apiKey: apiKey , system: system, controller: self, delegate: self, preMSISDN: preMsisdn)
}
```

Parameters passed:

| Name       | Type                  | Description                                                                                                                                                           |
| :--------- | :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| code       | String                | This is the code created by calling the Scan to Pay API representing the transaction.                                                                                 |
| apiKey     | String                | This is the API key provided by Scan to Pay that will enable the library to be used. This can be found on the Scan to Pay Portal under the Lib Lite Tokens menu item. |
| system     | MPSystem              | This value can be Live or Test, representing the Scan to Pay backend system to connect to.                                                                            |
| controller | UIViewController      | The presenting controller.                                                                                                                                            |
| delegate   | MPMasterPassDelegate  | The callback delegate that will receive the results.                                                                                                                  |
| preMsisdn  | String                | This is an optional field if you know the client’s mobile number.                                                                                                     |

## Calling the Preregister Method

The following snippet illustrates how to invoke the pre-register request from Swift:

```
import MasterPassKit

@IBAction func preRegister(sender: AnyObject) {
    let apiKey = "1234567890"
    let system = MPSystem.test

    let masterpass = MPMasterPass();
    masterpass.preRegister(apiKey, system:system, controller: self, delegate: self);
    
    //or

    let preMsisdn = "27123456789"
    masterpass.preRegister(apiKey, system:system, controller: self, delegate: self, preMSISDN: preMsisdn);
}
```

Parameters passed:

| Name       | Type                  | Description                                                                                                                                                           |
| :--------- | :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| apiKey     | String                | This is the API key provided by Scan to Pay that will enable the library to be used. This can be found on the Scan to Pay Portal under the Lib Lite Tokens menu item. |
| system     | MPSystem              | This value can be Live or Test, representing the Scan to Pay backend system to connect to.                                                                            |
| controller | UIViewController      | The presenting controller.                                                                                                                                            |
| delegate   | MPMasterPassDelegate  | The callback delegate that will receive the results.                                                                                                                  |
| preMsisdn  | String                | This is an optional field if you know the client’s mobile number                                                                                                      |

## Calling the Manage Card List

This method allows a 3rd party app to send a request to the Scan to Pay SDK in order for the cardholder to  
“manage” their card list. Once invoked, the user is then able to add or delete bank cards.

```
import MasterPassKit

@IBAction func manageCardList(sender: AnyObject) {
    let apiKey = "1234567890"
    let system = MPSystem.test

    let masterpass = MPMasterPass();
    masterpass.walletManagement(apiKey, system: system, controller: self, delegate: self);

    //or
    let preMsisdn = "27123456789"
    masterpass.walletManagement(apiKey, system: system, controller: self, delegate: self, preMSISDN: preMsisdn);
}
```

Parameters passed:

| Name       | Type                  | Description                                                                                                                                                           |
| :--------- | :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| apiKey     | String                | This is the API key provided by Scan to Pay that will enable the library to be used. This can be found on the Scan to Pay Portal under the Lib Lite Tokens menu item. |
| system     | MPSystem              | This value can be Live or Test, representing the Scan to Pay backend system to connect to.                                                                            |
| controller | UIViewController      | The presenting controller.                                                                                                                                            |
| delegate   | MPMasterPassDelegate  | The callback delegate that will receive the results.                                                                                                                  |
| preMsisdn  | String                | This is an optional field if you know the client’s mobile number                                                                                                      |

## Handling the Response

The following snippet illustrates how to implement the delegate to handle the response:

```
import UIKit
import MasterPassKit

class ViewController: UIViewController, MPMasterPassDelegate {

    func masterpassInvalidCode() {
        let alert = UIAlertController(
            title: "Masterpass Result",
            message: "Invalid Code",
            preferredStyle: .alert)
        alert.addAction(UIAlertAction(
            title: "Cancel",
            style: .cancel,
            handler: nil));
        self.present(
            alert,
            animated: true,
            completion: nil);
    }

    func masterpassError(_ error: MPError) {
        var alertMessage = "Error"
        switch error {
        case MPError.codeNotVariableAmount:
            alertMessage = "Code not variable amount error"
            break;
        case MPError.exceptionOccored:
            alertMessage = "Exception occured"
            break;
        case MPError.invalidApiKeyParameter:
            alertMessage = "Invalid key parameter"
            break;
        case MPError.invalidCodeParameter:
            alertMessage = "Invalid code parameter"
            break;
        case MPError.networkError:
            alertMessage = "Network error"
            break;
        case MPError.otpError:
            alertMessage = "OTP Error"
            break;
        case MPError.paymentError:
            alertMessage = "Payment error"
            break;
        case MPError.secureCodeNotSupported:
            alertMessage = "Secure code not supported"
            break;
        default:
            alertMessage = "Error"
        }
        let alert = UIAlertController(
            title: "Masterpass Result",
            message: alertMessage,
            preferredStyle: .alert)
        alert.addAction(UIAlertAction(
            title: "Cancel",
            style: .cancel,
            handler: nil));
        self.present(
            alert,
            animated: true,
            completion: nil);
    }

    func masterpassPaymentFailed(withTransactionReference transactionReference: String!) {
            let alert = UIAlertController(
                title: "Masterpass Result",
                message: "Payment Failed. Ref: \(transactionReference)",
                preferredStyle: .alert)
            alert.addAction(UIAlertAction(
                title: "Cancel",
                style: .cancel,
                handler: nil));
            self.present(
                alert,
                animated: true,
                completion: nil);
    }

    func masterpassPaymentSucceeded(withTransactionReference transactionReference: String!) {
            let alert = UIAlertController(
                title: "Masterpass Result",
                message: "Payment Succeeded. Ref: \(transactionReference)",
                preferredStyle: .alert)
            alert.addAction(UIAlertAction(
                title: "Cancel",
                style: .cancel,
                handler: nil));
            self.present(
                alert,
                animated: true,
                completion: nil);
    }

    func masterpassUserDidCancel() {
        let alert = UIAlertController(
            title: "Masterpass Result",
            message: "User did cancel",
            preferredStyle: .alert)
        alert.addAction(UIAlertAction(
            title: "Cancel",
            style: .cancel,
            handler: nil));
        self.present(
            alert,
            animated: true,
            completion: nil);
    }

    func masterpassUserRegistered() {
        let alert = UIAlertController(
            title: "Masterpass Result",
            message: "User registered",
            preferredStyle: .alert)
        alert.addAction(UIAlertAction(
            title: "Cancel",
            style: .cancel,
            handler: nil));
        self.present(
            alert,
            animated: true,
            completion: nil);
    }

    func masterpassUserCompletedWallet() {
        let alert = UIAlertController(
            title: "Masterpass Result",
            message: "User Done with Wallet",
            preferredStyle: .alert)
        alert.addAction(UIAlertAction(
            title: "Cancel",
            style: .cancel,
            handler: nil));
        self.present(
            alert,
            animated: true,
            completion: nil);
    }
}
```

The following is a breakdown of the delegate callback methods:

| Result Code                                         | Description                                          | Extra Values                                                                                                                                                |
| :-------------------------------------------------- | :--------------------------------------------------- | :---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| MPError                                    | Returned if an error has occurred before the payment | MPError – This enum indicates the type of error that occurred. See the error table below                                                                    |
| masterpassPaymentSucceededWithTransactionReference | Returned on payment  success                         | transactionReference - This is the reference for the transaction. This reference will be used to tie up the transaction on the 3rd party backend system.    |
| masterpassPaymentFailedWithTransactionReference    | Returned if they payment failed                      | transactionReference - This is the reference for the failed transaction in the event the 3rd party needs to request more information regarding the failure. |
| masterpassUserDidCancel                            | Returned if the user aborted the process             | None.                                                                                                                                                       |
| masterpassInvalidCode                              | Returned if the code that was passed is invalid      | None.                                                                                                                                                       |

## Loading Dialog

The MasterPassKit framework also offers a Loading dialog for any task that occurs just before invoking the checkout method. This gives a constant user experience. You may use this Dialog optionally.

See the code snippet below:

```
let masterpass = MPMasterPass();
masterpass.showLoadingDialog(from: self)
```

## Errors

All errors are defined in the MPError enum:

```
typedef NS_ENUM(NSInteger, MPError) {
    MPErrorNetworkError,
    MPErrorExceptionOccored,
    MPErrorPaymentError,
    MPErrorOTPError,
    MPErrorInvalidCodeParameter,
    MPErrorInvalidApiKeyParameter,
    MPErrorSecureCodeNotSupported,
    MPErrorCodeNotVariableAmount
};
```

## Integrate "Pay by card" button

The MasterPassKit framework also offers a "Pay by card" feature to make the payment using simple way like follow:

- Open your storyboard file.
- Drag and Drop `UIView` on your storyboard.
- Provide constraint to `UIView`, if needed.
- Provide the custom class `MPPayByCard` from the `Show the identity inspector` to `UIView` by selecting them.

![alt text](./Documents/Add_the_Custom_Class_MPPayByCard_to_UIView.png "Add the custom class MPPayByCard to UIView")

- On your `UIViewController` file create a variable like `@IBOutlet weak var payByCard: MPPayByCard!`
- Now assign `@IBOutlet` to your `UIView` by opening your storyboard file, and select the `UIView` where you have assigned the custom class `MPPayByCard`, select the option `Show the Connection inspector` from the `Inspectors` menu.

![alt text](./Documents/Add_IBOutlet_to_UIView.png "Add IBOutlet to UIView")

![alt text](./Documents/Add_IBOulet_to_MPPayByCard.png "Add IBOutlet to MPPayByCard")

- Now open your `UIViewController` file, add delegate `MPPayByCardDelegate` to `UIViewController`, and on `viewDidLoad` method add the following code snippet:

```
override func viewDidLoad() {
    super.viewDidLoad()
    payByCard.delegate = self
}
```

- Implement delegate method `didPayByCardTapped`

```
func didPayByCardTapped() {
    view.endEditing(true)
    let apiKey = "6799782555"
    let system = MPSystem.test
    let qrCode = "6799782555"
    let masterpass = MPMasterPass();
    masterpass.checkoutUsingPayByCard(withAPIKey: apiKey, system: system, delegate: self, application: UIApplication.shared, qrCode: qrCode)
}
```

Parameters passed:

| Name       | Type                  | Description                                                                                                                                                           |
| :--------- | :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| apiKey | String | This is the API key provided by Scan to Pay that will enable the library to be used. This can be found on the Scan to Pay Portal under the Lib Lite Tokens menu item. |
| system | MPSystem | This value can be Live or Test, representing the Scan to Pay backend system to connect to.|
| delegate | MPMasterPassDelegate | The callback delegate that will receive the results.|
| application | UIApplication | To find out the presenting controller.|
| qrCode | String | This is the code created by calling the Scan to Pay API representing the transaction.|

## Integrate "Pay by App" button

The MasterPassKit framework also offers a "Pay by App" feature to make the payment using supported applications. It will display the list of supported application to make the payment. To integrate perform the following steps:

- Open your target `info.plist` file and add the following code snippet to open the supported app to make the payments.

```
<key>LSApplicationQueriesSchemes</key>
<array>
    <string>masterpass.absa.scheme</string>
    <string>masterpass.sbsa.scheme</string>
    <string>masterpass.nedbank.scheme</string>
    <string>masterpass.spenda.scheme</string>
    <string>masterpass.capitec.scheme</string>
    <string>masterpass.vodapay.scheme</string>
    <string>nedbank</string>
    <string>https://www.online.fnb.co.za/banking/mobileservices?codetype=masterpassdeeplink</string>
</array>
```

- Open your storyboard file.
- Drag and Drop `UIView` on your storyboard.
- Provide constraint to `UIView`, if needed.
- Provide the custom class `MPPayByApp` from the `Show the identity inspector` to `UIView` by selecting them.

![alt text](./Documents/Add_the_Custom_Class_MPPayByApp_to_UIView.png "Add the custom class MPPayByApp to UIView")

- On your `UIViewController` file create a variable like `@IBOutlet weak var payByApp: MPPayByApp!`
- Now assign `@IBOutlet` to your `UIView` by opening your storyboard file, and select the `UIView` where you have assigned the custom class `MPPayByApp`, select the option `Show the Connection inspector` from the `Inspectors` menu.

![alt text](./Documents/Add_IBOutlet_to_UIView_1.png "Add IBOutlet to UIView")

![alt text](./Documents/Add_IBOulet_to_MPPayByApp.png "Add IBOutlet to MPPayByApp")

- Now open your `UIViewController` file, add delegate `MPPayByAppDelegate` to `UIViewController`, and on `viewDidLoad` method add the following code snippet:

```
override func viewDidLoad() {
    super.viewDidLoad()
    payByApp.delegate = self
}
```

- Implement delegate method `didPayByAppWithInfo`

```
func didPayByApp(withInfo appInfo: [AnyHashable : Any]?) {
    view.endEditing(true)
    let apiKey = "1234567890"
    let system = MPSystem.test
    let qrCode = "6799782555"
    let masterpass = MPMasterPass();
    masterpass.checkoutUsingPayByApp(withAPIKey: apiKey, system: system, delegate: self, withAppInfo: appInfo, application: UIApplication.shared, qrCode: qrCode, andCallback: "your.app.scheme://")
}
```

Parameters passed:

| Name       | Type                  | Description                                                                                                                                                           |
| :--------- | :-------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| apiKey | String | This is the API key provided by Scan to Pay that will enable the library to be used. This can be found on the Scan to Pay Portal under the Lib Lite Tokens menu item. |
| system | MPSystem | This value can be Live or Test, representing the Scan to Pay backend system to connect to.|
| delegate | MPMasterPassDelegate | The callback delegate that will receive the results.|
| appInfo | [AnyHashable : Any] | To help to open the supported application to make the payment.|
| application | UIApplication | To find out the presenting controller.|
| qrCode | String | This is the code created by calling the Scan to Pay API representing the transaction.|
| andCallback | String | This is the callback string which helps to open your app again on payment success or failure.|
