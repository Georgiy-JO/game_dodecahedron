# Model-View-Controller & Model-View-Presenter & Model-View-ViewModel patterns

## History

The concept of MVC was described by Trygve Reenskaug in 1978 while working on the Smalltalk programming language at Xerox PARC. Steve Burbeck later implemented the pattern in Smalltalk-80. The final version of the MVC concept was not published until 1988 in Technology Object magazine. After that, the design pattern began to evolve. For example, a hierarchical version of HMVC was introduced; MVA, MVVM.

## MVC (Model-View-Controller) Pattern

The Model-View-Controller (MVC) pattern is a scheme for dividing application modules into three separate macro components: a model that contains the business logic, a view - a form of user interface for interacting with the program, and a controller that modifies the model based on user actions.

### Main idea 

The main need for this pattern is related to the developers' desire to separate the program's business logic from the views, which allows them to easily replace views and reuse once-implemented logic in other contexts. A model that is separate from the view and a controller that interacts with it allows you to efficiently reuse or modify code that has already been written.

### Elements

#### The model

The **model** stores and accesses key data, performs operations defined by the program's business logic, and manages the part of the program responsible for all algorithms and information handling processes. These models, when modified by the controller, affect the display of information on the user interface view. The class library that implements the logic of *The S-Snake* (*The Te-Tris*, etc) game must act as a model in this program. This library must provide all the necessary classes and methods to execute the game mechanics. This is the business logic of this program, as it provides the means to solve the problem.

#### The controller

The **controller** is a thin macro component that performs the modification of the model. All requests for model changes are generated through the controller. It looks like a kind of "facade" for the model in the code, that is, a set of methods that already work directly with the model. It is called thin because the ideal controller contains no additional logic other than calling one or more methods of the model. The controller acts as a link between the interface and the model. This allows the model to be completely encapsulated from the view. Such separation is useful because it allows the view code to know nothing about the model code and to refer only to the controller, whose interface of provided functions is unlikely to change significantly. The model, on the other hand, can change significantly, and when "moving" to other algorithms, technologies, or even programming languages in the model, only a small portion of the code in the controller directly related to the model needs to be changed. Otherwise, it is likely that much of the interface code would have to be rewritten, as it is highly dependent on the model implementation. Thus, when the user interacts with the interface, he or she calls controller methods that modify the model.

#### The view 

The **view** contains all the code associated with the program interface. There should be no business logic in the code of a perfect interface. It is just a form for user interaction.

![MVC-Process](/misc/images/MVC-Process.png)

## MVP (Model-View-Presenter) Pattern

The MVP pattern shares two components with MVC: model and view. However, it replaces the controller with a presenter.

The presenter implements the interaction between the model and the view. When the view notifies the presenter that the user has done something (e.g., pressed a button), the presenter decides to update the model and synchronizes all changes between the model and the view. However, the presenter does not communicate directly with the view. Instead, it communicates through an interface. This allows all components of the application to be tested individually afterwards.

![MVP-Process](/misc/images/MVP-Process.png)

### MVVM (Model-View-ViewModel) Pattern 

MVVM is a more modern evolution of MVC. The main goal of MVVM is to provide a clear separation between the view and model layers.

MVVM supports bi-directional data binding between View and ViewModel components.

The view acts as a subscriber to property value change events provided by the ViewModel. When a property in the view model changes, it notifies all subscribers, and the view in turn requests the updated property value from the view model.  When the user interacts with an UI element, the view calls the appropriate command provided by the view model.

A view model is both an abstraction of a view and a wrapper of data from the model to be bound. In other words, it contains the model that has been transformed into the view, as well as the commands that the view can use to manipulate the model.

![MVVM-Process](/misc/images/MVVM-Process.png)
