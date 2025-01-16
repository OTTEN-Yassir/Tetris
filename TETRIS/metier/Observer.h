#ifndef OBSERVER_H
#define OBSERVER_H
/**
 *  @brief Subject class
 */
class Subject;


/**
 * \brief Basic abstract class of any observer.
 *
 * Class from which all listeners (or "observers") of the
 * design "Observer / SubjectObservation".
 *
 * \sa Subject.
 * \see https://en.wikipedia.org/wiki/Observer_pattern
 */
class Observer {
public:


    virtual ~Observer(){};

    /*!
     * \brief Pure virtual method that each concrete observer must
     * implement: it is this method that the observed subject calls when
     * a notification.
     *
     * \param subject the subject of observation that notifies a change.
     * \see Subject::notifyObservers().
     */
    virtual void Update(const Subject *) = 0;


protected:

    Observer () = default;
};

#endif // OBSERVER_H
