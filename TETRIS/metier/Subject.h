#ifndef SUBJECT_H
#define SUBJECT_H
#include <set>
#include "Observer.h"
//class Observer;

/*!
 * \brief Basic class of any "subject of observation".
 *
 * Class from which any event source (or "observation subject") is derived
 * of the "Observer / ObservationSubject" design model.
 *
 */
class Subject {



public:


    /*!
     * \brief Virtual destructor by default because polymorphic use.
     */
    virtual ~Subject(){};

    /*!
     * \brief Method allowing an observer to record himself as
     * listener of the subject of observation.
     *
     * \param observe a pointer to the observing candidate.
     */
    virtual void Attach(Observer *observer) = 0;



    /*!
     * \brief Method allowing an observer to withdraw from the list
     * of the listener of the subject of observation.
     *
     * \param observe the skill of the disinterested observer.
     */
    virtual void Detach(Observer *observer) = 0;

    /*!
     * \brief A method that warns the observers of a
     * change of state of the subject of observation, by invoking their
     * method Observer::update().
     *
     * \sa Observer::update(const Subject *).
     */
    virtual void Notify()const = 0;


protected:

    /*!
   * \brief The set of registered observers.
   */
    std::set<Observer *> observers_ {};
};

#endif // SUBJECT_H
